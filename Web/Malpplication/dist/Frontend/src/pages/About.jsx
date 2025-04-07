import React from "react";
import { Helmet } from "react-helmet";
import {
    Card,
    CardHeader,
    CardBody,
    Divider,
    User,
    Link,
} from "@nextui-org/react";
import ReactPlayer from "react-player/lazy";

const names = ["CX330", "popo8712"];
const links = ["https://cx330.tw", "https://github.com/popo8712"];
const links_name = ["CX330Blake", "popo8712"];
const avatars = [
    "https://avatars.githubusercontent.com/u/108129644?s=96&v=4",
    "https://avatars.githubusercontent.com/u/161846035?v=4",
];
const text = [
    "A Hacker/Developer/CTFer/Undergraduate student from Taiwan. Happy hacking!",
    "A healthy developer who balances coding and well-being.",
];

export default function About() {
    return (
        <>
            <Helmet>
                <title>About | 1337 Works</title>
            </Helmet>
            <br />
            <p className="text-5xl flex justify-center font-bold font-mono">
                How to Start
            </p>
            <br />
            <p className="text-lg flex justify-start w-1/2 mx-auto font-mono">
                This website emulates the job finding websites like 104 or
                something like that, and it's a vulnarable website only for
                security testing. You can go to the resume page to start testing
                the vulnerability. There's no need to waste time on other pages.
            </p>
            <br />
            <p className="text-lg flex justify-start w-1/2 mx-auto font-mono">
                Recommended Site:&nbsp;
                <strong>
                    <a
                        href="https://portswigger.net/web-security/file-upload"
                        type="_blank"
                    >
                        <u>PortSwigger's website</u>
                    </a>
                </strong>
            </p>
            <br />
            <p className="text-lg flex justify-start w-1/2 mx-auto font-mono">
                Also, as a hint, you can check the following video.
            </p>
            <br />
            <ReactPlayer
                url={"https://www.youtube.com/watch?v=YAFVGQ-lBoM"}
                playing={false}
                controls={true}
                loop={true}
                width={"50%"}
                className="flex justify-center mx-auto"
            />
            <br />
            <br />
            <p className="text-5xl flex justify-center font-bold font-mono">
                Our Members
            </p>
            <br />
            {names.map((name, index) => (
                <React.Fragment key={index}>
                    <Card className="w-1/3 flex justify-center mx-auto">
                        <CardHeader>
                            <User
                                name={name}
                                description={
                                    <Link
                                        href={links[index]}
                                        size="sm"
                                        isExternal
                                        className="text-secondary"
                                    >
                                        {`@${links_name[index]}`}
                                    </Link>
                                }
                                avatarProps={{
                                    src: avatars[index],
                                    size: "lg",
                                }}
                                className="flex justify-start"
                            />
                        </CardHeader>
                        <Divider />
                        <CardBody>{text[index]}</CardBody>
                    </Card>
                    <br />
                </React.Fragment>
            ))}
            <br />
            <br />
            <br />
        </>
    );
}
