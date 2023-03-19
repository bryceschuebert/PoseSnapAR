import React from 'react';
import '../../styles/projects/projectCard.css';

function ProjectCard({ project, selected, onClick }) {
  return (
    <div
      className={`project-card ${selected ? 'selected' : ''}`}
      onClick={onClick}
    >
      <img src={project.imageUrl} alt={project.name} />
      <h4 className="project-name">{project.name}</h4>
    </div>
  );
}

export default ProjectCard;

