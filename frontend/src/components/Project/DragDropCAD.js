// DragDropCAD.js
import React, { useCallback } from 'react';
import { useDropzone } from 'react-dropzone';
import { Modal } from 'antd';
import ConversionProgress from './ConversionProgress';
import * as THREE from 'three';
import { GLTFLoader } from 'three-gltf-loader';

const DragDropCAD = ({ onCADFiles, visible, onCancel }) => {
  const [conversionInProgress, setConversionInProgress] = React.useState(false);


  const loadConvertedModel = async (modelData) => {
    const loader = new GLTFLoader();
    const object = await new Promise((resolve, reject) => {
      loader.parse(modelData, '', (obj) => resolve(obj), (error) => reject(error));
    });
  
    // Process the loaded object (e.g., add it to the scene)
    console.log(object);
  };

  const onDrop = useCallback(
    async (acceptedFiles) => {
      const cadFiles = acceptedFiles.filter(
        (file) => file.type === 'model/iges' || file.type === 'model/step'
      );
  
      if (cadFiles.length > 0) {
        const formData = new FormData();
        formData.append('cadFile', cadFiles[0]);
  
        try {
          const response = await fetch('http://localhost:3001/convert', {
            method: 'POST',
            body: formData,
          });
  
          if (response.ok) {
            const modelData = await response.arrayBuffer();
            loadConvertedModel(modelData);
            onCADFiles(cadFiles);
            setConversionInProgress(true);
          } else {
            console.error('Error converting CAD file');
          }
        } catch (error) {
          console.error('Error sending CAD file to server:', error);
        }
      }
    },
    [onCADFiles]
  );
  

  const { getRootProps, getInputProps, isDragActive } = useDropzone({ onDrop });

  return (
    <>
      <Modal
        title="Drag and Drop CAD Files"
        visible={visible} // Use the 'visible' prop for the modal's visibility
        onCancel={onCancel} // Use the 'onCancel' prop for the modal's cancel function
        footer={null}
        centered
      >
        <div {...getRootProps()} className={`dropzone ${isDragActive ? 'active' : ''}`}>
          <input {...getInputProps()} />
          {isDragActive ? (
            <p>Drop the CAD files here...</p>
          ) : (
            <p>Drag and drop CAD files here, or click to select files</p>
          )}
        </div>
        {conversionInProgress && <ConversionProgress />}
      </Modal>
    </>
  );
};

export default DragDropCAD;




