import "./App.css";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Home from "./pages/Home";
import About from "./pages/About";
import Jobs from "./pages/Jobs";
import NotFound from "./pages/NotFound";
import Navbar from "./components/Navbar";
import { NextUIProvider } from "@nextui-org/react";
import React, { useState, useEffect } from "react";
import Resume from "./pages/Resume";

function App() {
    const [isDarkMode, setIsDarkMode] = useState(true);

    useEffect(() => {
        // Get the preference theme from local storage
        const savedTheme = localStorage.getItem("theme");
        if (savedTheme) {
            setIsDarkMode(savedTheme === "dark");
        }
    }, []);

    useEffect(() => {
        // Save the theme preference to local storage
        localStorage.setItem("theme", isDarkMode ? "dark" : "light");
        document.documentElement.className = isDarkMode ? "dark" : "light";
    }, [isDarkMode]);

    const toggleDarkMode = () => {
        setIsDarkMode(!isDarkMode);
    };

    return (
        <NextUIProvider>
            <main className={isDarkMode ? "dark" : "light"}>
                <React.StrictMode>
                    <div>
                        <BrowserRouter>
                            <Navbar
                                isDarkMode={isDarkMode}
                                toggleDarkMode={toggleDarkMode}
                            />
                            <div>
                                <br />
                                <Routes>
                                    <Route index element={<Home />} />{" "}
                                    <Route path="/home" element={<Home />} />{" "}
                                    <Route path="/about" element={<About />} />{" "}
                                    <Route path="/jobs" element={<Jobs />} />{" "}
                                    <Route path="*" element={<NotFound />} />{" "}
                                    <Route
                                        path="/resume"
                                        element={<Resume />}
                                    />
                                </Routes>
                            </div>
                        </BrowserRouter>
                    </div>
                </React.StrictMode>
            </main>
        </NextUIProvider>
    );
}

export default App;
