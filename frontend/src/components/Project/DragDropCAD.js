// DragDropCAD.js
import React, { useCallback } from 'react';
import { useDropzone } from 'react-dropzone';
import { Modal, Button } from 'antd';
import ConversionProgress from './ConversionProgress';
import * as THREE from 'three';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';

const DragDropCAD = ({ onCADFiles, visible, onCancel }) => {
  const [conversionInProgress, setConversionInProgress] = React.useState(false);
  const [attachedFileName, setAttachedFileName] = React.useState('');
  const [cadFiles, setCadFiles] = React.useState([]);

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
      setAttachedFileName('');
      const cadFiles = acceptedFiles.filter((file) => {
        const ext = file.name.split('.').pop().toLowerCase();
        return ext === 'iges' || ext === 'igs' || ext === 'step' || ext === 'stp';
      });
  
      if (cadFiles.length > 0) {
        setAttachedFileName(cadFiles[0].name);
        setCadFiles(cadFiles);
      }      
    },
    []
  );
  
  const handleFileUpload = async () => {
    if (attachedFileName) {
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
  };
  
  

  const { getRootProps, getInputProps, isDragActive } = useDropzone({ onDrop });

  return (
    <>
      <Modal
        title="Drag and Drop CAD Files"
        visible={visible} // Use the 'visible' prop for the modal's visibility
        onCancel={() => {
          setAttachedFileName('');
          setCadFiles([]);
          onCancel();
        }}
        footer={
          <>
            {attachedFileName && (
              <Button
                type="primary"
                onClick={() => {
                  handleFileUpload();
                  onCancel();
                }}                
              >
                OK
              </Button>
            )}
            <Button onClick={onCancel}>Cancel</Button>
          </>
        }        
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
        <p>{attachedFileName ? `Attached file: ${attachedFileName}` : ''}</p>
        {conversionInProgress && <ConversionProgress />}
      </Modal>
    </>
  );
};

export default DragDropCAD;




