const express = require('express');
const multer = require('multer');
const fs = require('fs');
const path = require('path');
const cadexchanger = require('./build/Release/cadexchanger');

const app = express();
const upload = multer({ dest: 'uploads/' });

const port = process.env.PORT || 3001;

app.post('/convert', upload.single('cadFile'), (req, res) => {
    const inputFilePath = req.file.path;
    const outputFilePath = path.join('uploads', `${req.file.filename}.gltf`);

    if (cadexchanger.convertCADtoGLTF(inputFilePath, outputFilePath)) {
        res.sendFile(path.resolve(outputFilePath), { headers: { 'Content-Type': 'application/octet-stream' } }, () => {
            fs.unlink(inputFilePath, () => {});
            fs.unlink(outputFilePath, () => {});
        });
    } else {
        res.status(500).send('Error converting CAD file.');
    }
});

app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});


  
