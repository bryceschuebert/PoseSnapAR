// ProjectGrid.js
import React from 'react';
import ProjectCard from './ProjectCard';
import '../../styles/projects/projectGrid.css';

const ProjectGrid = ({ projects }) => {
  return (
    <div className="project-grid">
      <div className="button-row">
        {/* Add button functionality */}
        <button>Select All</button>
        <button>Delete</button>
        <button>Upload</button>
        <button>New</button>
      </div>
      <div className="projects">
        {projects.map((project) => (
          <ProjectCard key={project.id} project={project} />
        ))}
      </div>
    </div>
  );
};

export default ProjectGrid;
