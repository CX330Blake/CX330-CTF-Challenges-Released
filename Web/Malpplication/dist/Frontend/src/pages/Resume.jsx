import { Helmet } from "react-helmet";
import React, { useState } from "react";
import { message } from "antd";
import { Button } from "@mui/material";
import CloudUploadIcon from "@mui/icons-material/CloudUpload";
import CheckCircleIcon from "@mui/icons-material/CheckCircle";
import { styled } from "@mui/material/styles";
import { CheckCircle } from "@mui/icons-material";
import { document } from "postcss";

const VisuallyHiddenInput = styled("input")({
    clip: "rect(0 0 0 0)",
    clipPath: "inset(50%)",
    height: 1,
    overflow: "hidden",
    position: "absolute",
    bottom: 0,
    left: 0,
    whiteSpace: "nowrap",
    width: 1,
});

export default function Resume() {
    const [file, setFile] = useState(null);
    const [fileName, setFileName] = useState("");
    const [fileUrl, setFileUrl] = useState("");
    const [uploadSuccess, setUploadSuccess] = useState(null);
    const [errorMessage, setErrorMessage] = useState("");

    // Handle file select
    const handleFileChange = (e) => {
        const selectedFile = e.target.files[0];
        if (selectedFile) {
            setFile(selectedFile);
            setErrorMessage(selectedFile.name);
            setUploadSuccess(false);
        }
    };

    // Handle file submit
    const handleSubmit = async (e) => {
        e.preventDefault();
        if (!file) {
            setErrorMessage("Please Select a File");
            return;
        }
        setErrorMessage("Loading...pls wait");

        const timeoutMs = 3000;
        const controller = new AbortController();
        const timeoutId = setTimeout(() => controller.abort(), timeoutMs);

        // Upload
        const formData = new FormData();
        formData.append("file", file);

        try {
            const host = window.location.hostname; // 瀏覽器當前域名
            const response = await fetch(`http://${host}:1337/upload.php`, {
                method: "POST",
                body: formData,
                signal: controller.signal,
            });

            clearTimeout(timeoutId);

            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }

            const data = await response.json();

            if (data.status !== "success") {
                setErrorMessage(data.message);
                throw new Error(data.message || "Upload Failed");
            }

            const fileUrl = data.message;
            setFileName("");
            setFileUrl(fileUrl);
            setUploadSuccess(true);
            setErrorMessage("");
        } catch (error) {
            clearTimeout(timeoutId);
            console.error("Upload error:", error);

            if (error.name === "AbortError") {
                setErrorMessage("❌ Request timed out");
            }
            setUploadSuccess(false);
            setFileUrl("");
        }
    };

    return (
        <>
            <Helmet>
                <title>Resume | 1337 Works</title>
            </Helmet>
            <br />
            <div className="flex justify-center">
                <div className="flex flex-col justify-center items-center w-2/3">
                    <p className="text-2xl md:text-4xl text-center font-mono">
                        Looking for a better position? New graduated college
                        student?{" "}
                        <strong className="text-2xl md:text-4xl text-secondary">
                            Submit Your RESUME
                        </strong>{" "}
                        to find an opportunity!
                    </p>
                    <br />
                    <br />
                    <Button
                        component="label"
                        role={undefined}
                        // variant="contained"
                        variant="contained"
                        tabIndex={-1}
                        startIcon={<CloudUploadIcon />}
                        color="success"
                        className="flex justify-center font-mono"
                        size="large"
                    >
                        Select a file
                        <VisuallyHiddenInput
                            type="file"
                            onChange={handleFileChange}
                            multiple
                        />
                    </Button>
                    <p className="text-xl font-mono">
                        <br /> {errorMessage}
                    </p>
                    <br />
                    <Button
                        variant="contained"
                        color="error"
                        startIcon={<CheckCircle />}
                        onClick={handleSubmit}
                        size="large"
                        className="font-mono text-xl"
                    >
                        Upload
                    </Button>
                    <br />
                    <br />
                    {uploadSuccess === true && fileUrl ? (
                        <p
                            className="text-2xl font-mono text-green-500"
                            id="upload-message"
                        >
                            <a
                                href={fileUrl}
                                target="_blank"
                                rel="noopener noreferrer"
                            >
                                <u>✅ Your File is Here</u>
                            </a>
                        </p>
                    ) : null}
                </div>
            </div>
        </>
    );
}
