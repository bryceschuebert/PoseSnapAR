import React from 'react';
import { Outlet, useLocation } from 'react-router-dom';
import CADFileDropzone from './CADFIleDropzone';

const ProjectContainer = () => {
  const location = useLocation();

  const handleNewProject = (files) => {
    console.log('New project:', files);
  };

  return (
    <>
      {location.pathname === '/projects' && <CADFileDropzone onDrop={handleNewProject} />}
      <Outlet />
    </>
  );
};

export default ProjectContainer;
