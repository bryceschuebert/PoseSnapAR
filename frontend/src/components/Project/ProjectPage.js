import React, { useState } from "react";
import ProjectModal from "./ProjectModal";
import Questionnaire from "./Questionnaire";
import CADViewer from "./CADViewer";

const ProjectPage = () => {
  const [projectModalVisible, setProjectModalVisible] = useState(false);
  const [selectedProject, setSelectedProject] = useState(null);
  const [questionnaireAnswers, setQuestionnaireAnswers] = useState({});

  const handleProjectSelection = (project) => {
    setSelectedProject(project);
    setProjectModalVisible(false);
  };

  const handleQuestionnaireCompletion = (answers) => {
    setQuestionnaireAnswers(answers);
  };

  return (
    <div>
      <ProjectModal
        visible={projectModalVisible}
        onSelectProject={handleProjectSelection}
        onCancel={() => setProjectModalVisible(false)}
      />
      {selectedProject && !questionnaireAnswers && (
        <Questionnaire onSubmit={handleQuestionnaireCompletion} />
      )}
      {selectedProject && questionnaireAnswers && (
        <CADViewer
          project={selectedProject}
          answers={questionnaireAnswers}
        />
      )}
    </div>
  );
};

export default ProjectPage;

