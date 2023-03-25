// App.js

import React, { useState } from 'react';
import { Route, Routes, useLocation, useNavigate } from 'react-router-dom';
import { useAuth0 } from '@auth0/auth0-react';
import Loading from './components/Loading';
import Account from './components/Account';
import ProjectPage from './components/Project/ProjectPage';
import Navbar from './components/Navigation/Navbar';
import HomePage from './components/HomePage';
import LoginSignUp from './components/Navigation/LoginSignUp';
import MobileWarning from './components/MobileWarning';
import Questionnaire from './components/Project/Questionnaire';
import PoseProject from './components/Project/PoseProject';
import CompareProject from './components/Project/CompareProject';
import ProtectedRoute from "./components/ProtectedRoute";
import DragDropCAD from './components/Project/DragDropCAD';

function App() {
  const { isLoading } = useAuth0();
  const location = useLocation();
  const navigate = useNavigate(); 
  const [cadFiles, setCadFiles] = useState([]);

  const [isQuestionnaireVisible, setIsQuestionnaireVisible] = useState(false);
  const [isDragDropVisible, setIsDragDropVisible] = useState(false);

  const handleNewProject = (files) => {
    console.log('New project:', files);
    setCadFiles(files);
    setIsQuestionnaireVisible(true);
  };

  const handleQuestionnaireSubmit = (values) => {
    console.log('Questionnaire submitted:', values);
    setIsQuestionnaireVisible(false);
  
    if (values.projectType === 'pose') {
      navigate('/projects/pose');
    } else if (values.projectType === 'compare') {
      navigate('/projects/compare');
    }
    setIsDragDropVisible(true); // Show the DragDropCAD component
  }; 
  
  const handleQuestionnaireCancel = () => {
    setIsQuestionnaireVisible(false);
    setIsDragDropVisible(false);
  };  

  const handleOpenProject = (files) => {
    console.log('Open project:', files);
  };

  const handleCADFiles = (cadFiles) => {
    console.log('CAD files received:', cadFiles);
    setIsDragDropVisible(false);
  };

  if (isLoading) {
    return <Loading />;
  }

  return (
    <div className="App">
      <MobileWarning />
      {location.pathname !== '/login-signup' && (
        <Navbar onNewProject={handleNewProject} onOpenProject={handleOpenProject} />
      )}
      <Questionnaire
        onSubmit={handleQuestionnaireSubmit}
        onCancel={handleQuestionnaireCancel}
        visible={isQuestionnaireVisible}
      />
      {isDragDropVisible && <DragDropCAD onCADFiles={handleCADFiles} />}
        <Routes>
          <Route path="/" element={<ProtectedRoute />}>
            <Route index element={<HomePage />} />
            <Route path="account" element={<Account />} />
            <Route path="projects" element={<ProjectPage />} />
            <Route path="projects/pose" element={<PoseProject />} />
            <Route path="projects/compare" element={<CompareProject />} />
          </Route>
          <Route path="/login-signup" element={<LoginSignUp />} />
        </Routes>
    </div>
  );
}

export default App;







