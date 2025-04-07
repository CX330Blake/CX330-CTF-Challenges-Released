// tailwind.config.js
const { nextui } = require("@nextui-org/react");

/** @type {import('tailwindcss').Config} */
module.exports = {
    mode: "jit",
    content: [
        // ...
        "./node_modules/@nextui-org/theme/dist/**/*.{js,ts,jsx,tsx}",
        "./src/**/*.{js,ts,jsx,tsx}",
    ],
    theme: {
        extend: {
            colors: {
                primary: "#282A36",
                secondary: "#BD93F9",
            },
        },
        // screens: {
        //     sm: "500px",
        // },
    },
    darkMode: "class",
    plugins: [nextui()],
};
