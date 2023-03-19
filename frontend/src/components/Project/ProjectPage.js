// ProjectPage.js
import React from 'react';
import ProjectGrid from './ProjectGrid';

const projects = [
  { id: 1, name: 'Project 1', imageUrl: 'https://via.placeholder.com/150' },
  { id: 2, name: 'Project 2', imageUrl: 'https://via.placeholder.com/150' },
];

const ProjectPage = () => {
  return (
    <div>
      <ProjectGrid projects={projects} />
    </div>
  );
};

export default ProjectPage;




