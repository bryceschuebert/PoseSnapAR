const path = require('path');
const convertCAD = require('./cadexchanger/build/Release/cadexchanger').wrapperFunction;

const inputFilePath = path.join(__dirname, 'backend/tempfiles/differetialrt.stp'); // Replace with the actual path
const outputFilePath = path.join(__dirname, 'backend/tempfiles'); // Replace with the actual path
const fileType = 'model/step'; // Change to 'model/iges' if you're testing an IGES file

console.log(`Converting file ${inputFilePath} to ${outputFilePath}`);

if (convertCAD(inputFilePath, fileType, outputFilePath)) {
    console.log('File converted successfully:', outputFilePath);
} else {
    console.error('Error converting CAD file');
}
