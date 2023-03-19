// ProjectCard.js
import React, { useState } from 'react';
import '../../styles/projects/projectCard.css';

const ProjectCard = ({ project }) => {
  const [isEditing, setIsEditing] = useState(false);
  const [projectName, setProjectName] = useState(project.name);

  const handleNameChange = (e) => {
    setProjectName(e.target.value);
  };

  const toggleEditMode = () => {
    setIsEditing(!isEditing);
  };

  return (
    <div className="project-card">
      <div className="project-image">
        <img src={project.imageUrl} alt={project.name} />
      </div>
      {isEditing ? (
        <input
          type="text"
          value={projectName}
          onChange={handleNameChange}
          onBlur={toggleEditMode}
          autoFocus
        />
      ) : (
        <h4 onClick={toggleEditMode}>{projectName}</h4>
      )}
      <p>Last Update: {project.lastUpdate}</p>
    </div>
  );
};

export default ProjectCard;
