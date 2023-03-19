import React, { useState } from "react";
import ProjectCard from "./ProjectCard";
import "../../styles/projects/projectGrid.css";

function ProjectGrid() {
  const projects = [
    { id: 1, name: "Project 1", imageUrl: "https://via.placeholder.com/150" },
    { id: 2, name: "Project 2", imageUrl: "https://via.placeholder.com/150" },
  ];

  const [selectedProjects, setSelectedProjects] = useState([]);
  const [selectAll, setSelectAll] = useState(false);

  const handleProjectClick = (id) => {
    if (selectedProjects.includes(id)) {
      setSelectedProjects(selectedProjects.filter((projectId) => projectId !== id));
    } else {
      setSelectedProjects([...selectedProjects, id]);
    }
  };

  const handleSelectAll = () => {
    setSelectAll(!selectAll);
    if (!selectAll) {
      setSelectedProjects(projects.map((project) => project.id));
    } else {
      setSelectedProjects([]);
    }
  };

  const handleDelete = () => {
    if (window.confirm("Are you sure you want to delete the selected projects?")) {
      // Delete the selected projects from the actual data source (e.g., API, database)
      console.log("Deleted projects:", selectedProjects);
      setSelectedProjects([]);
    }
  };

  return (
    <div>
      <div className="button-row">
        <button onClick={handleSelectAll}>Select All</button>
        <div>
          <button
            className={selectedProjects.length > 0 ? "delete-btn" : ""}
            onClick={handleDelete}
          >
            Delete
          </button>
          <button>New</button>
          <button>Upload</button>
        </div>
      </div>
      <div className="project-grid">
        {projects.map((project) => (
          <ProjectCard
            key={project.id}
            project={project}
            onClick={() => handleProjectClick(project.id)}
            selected={selectedProjects.includes(project.id)}
          />
        ))}
      </div>
    </div>
  );
}

export default ProjectGrid;

