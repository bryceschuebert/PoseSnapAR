// ProjectPage.js
import React, { useState } from "react";
import CompareProject from "./CompareProject";
import ProjectPose from "./PoseProject";
import Questionnaire from './Questionnaire';


const ProjectPage = () => {
  const [selectedProjectType, setSelectedProjectType] = useState(null);

  const handleQuestionnaireCompletion = (projectType) => {
    setSelectedProjectType(projectType);
  };

  return (
    <div>
      {!selectedProjectType && (
        <Questionnaire onSubmit={handleQuestionnaireCompletion} />
      )}
      {selectedProjectType === "pose" && <ProjectPose />}
      {selectedProjectType === "compare" && <CompareProject />}
    </div>
  );
};

export default ProjectPage;

