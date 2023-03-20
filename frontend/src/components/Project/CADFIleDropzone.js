import React, { useCallback } from 'react';
import { useDropzone } from 'react-dropzone';

const CADFileDropzone = ({ onDrop }) => {
  const handleDrop = useCallback((acceptedFiles) => {
    onDrop(acceptedFiles);
  }, [onDrop]);

  const { getRootProps, getInputProps, isDragActive } = useDropzone({ onDrop: handleDrop });

  return (
    <div {...getRootProps()} style={{ border: '1px solid #ccc', padding: '20px' }}>
      <input {...getInputProps()} />
      {isDragActive ? (
        <p>Drop the CAD files here...</p>
      ) : (
        <p>Drag and drop CAD files here, or click to select files</p>
      )}
    </div>
  );
};

export default CADFileDropzone;
