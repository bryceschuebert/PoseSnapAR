const express = require('express');
const multer = require('multer');
const fs = require('fs');
const path = require('path');
const convertCAD = require('./cadexchanger/build/Release/cadexchanger').wrapperFunction;
const cors = require('cors'); // Add this line

const app = express();
app.use(cors());
const upload = multer({ dest: 'uploads/' });

const port = process.env.PORT || 3001;

app.post('/convert', upload.single('cadFile'), (req, res) => {
    console.log("Received file:", req.file); // Log the received file
  
    const inputFilePath = req.file.path;
    const outputFilePath = path.join('uploads', `${req.file.filename}.gltf`);
  
    const fileExtension = path.extname(inputFilePath).toLowerCase();
    let fileType = '';
    switch (fileExtension) {
        case '.step':
        case '.stp':
            fileType = 'model/step';
            break;
        case '.iges':
        case '.igs':
            fileType = 'model/iges';
            break;
        default:
            res.status(400).send('Unsupported CAD file format.');
            return;
    }
  
    console.log("Converting file:", inputFilePath, "to", outputFilePath, "with fileType:", fileType);

    // Use the convertCAD function
    if (convertCAD(inputFilePath, fileType, outputFilePath)) {
      console.log("File converted successfully");
      res.sendFile(path.resolve(outputFilePath), { headers: { 'Content-Type': 'application/octet-stream' } }, () => {
          fs.unlink(inputFilePath, () => {});
          fs.unlink(outputFilePath, () => {});
      });
    } else {
      console.error("Error converting CAD file");
      res.status(500).send('Error converting CAD file.');
    }
  });
  
  app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
  });
  



  
