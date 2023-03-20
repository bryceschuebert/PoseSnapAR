import React, { useState } from 'react';
import { Button } from 'antd';
import ProjectModal from '../Project/ProjectModal';

const OpenButton = () => {
  const [isModalVisible, setModalVisible] = useState(false);

  const handleOpenClick = () => {
    setModalVisible(true);
  };

  const handleCancelModal = () => {
    setModalVisible(false);
  };

  const handleSelectProject = (projectData) => {
    console.log(`Selected project: ${projectData}`);
    // Do something with projectData, like opening the selected project
    setModalVisible(false);
  };

  return (
    <>
      <Button type="text" onClick={handleOpenClick}>
        Open
      </Button>
      <ProjectModal
        visible={isModalVisible}
        onSelectProject={handleSelectProject}
        onCancel={handleCancelModal}
      />
    </>
  );
};

export default OpenButton;
