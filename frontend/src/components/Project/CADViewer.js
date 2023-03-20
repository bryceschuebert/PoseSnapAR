import React, { useEffect } from "react";

const CADViewer = ({ cadModelUrl }) => {
  useEffect(() => {
    // Initialize your CAD viewer library here, and load the model from `cadModelUrl`
  }, [cadModelUrl]);

  return <div id="cad-viewer-container" style={{ width: "100%", height: "100%" }} />;
};

export default CADViewer;
