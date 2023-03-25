// Questionnaire.js
import React from "react";
import { Form, Button, Modal, Card, Space } from "antd";
import { SwapOutlined, RetweetOutlined } from "@ant-design/icons";
import DragDropCAD from "./DragDropCAD"; // Import the DragDropCAD component

const Questionnaire = ({ onSubmit, visible, onCancel }) => {
  const [selectedProjectType, setSelectedProjectType] = React.useState(null);
  const [showCADModal, setShowCADModal] = React.useState(false); // Add the state for the DragDropCAD modal visibility

  const handleProjectTypeSelection = (projectType) => {
    setSelectedProjectType(projectType);
  };

  const handleSubmit = () => {
    onSubmit(selectedProjectType);
    setShowCADModal(true); // Set the DragDropCAD modal visibility to true when submitting the form
  };

  const handleCADModalClose = () => {
    setShowCADModal(false); // Set the DragDropCAD modal visibility to false when closing the modal
  };

  // Render the modal with the questionnaire
  return (
    <>
      <Modal
        title="New Project"
        visible={visible} // The modal's visibility is controlled by the 'visible' prop
        onCancel={onCancel} // The modal's cancel function is controlled by the 'onCancel' prop
        footer={null}
        centered
      >
        <Space direction="vertical" style={{ width: "100%" }}>
          <div style={{ display: "flex", justifyContent: "space-between" }}>
            {/* Card for selecting the "pose" project type */}
            <Card
              style={{
                width: "45%",
                padding: "1rem",
                borderColor: selectedProjectType === "pose" ? "#1890ff" : undefined,
                borderWidth: selectedProjectType === "pose" ? 2 : undefined,
              }}
              hoverable
              onClick={() => handleProjectTypeSelection("pose")}
            >
              <SwapOutlined style={{ fontSize: "2rem" }} />
              <h3>Pose</h3>
            </Card>
            {/* Card for selecting the "compare" project type */}
            <Card
              style={{
                width: "45%",
                padding: "1rem",
                borderColor: selectedProjectType === "compare" ? "#1890ff" : undefined,
                borderWidth: selectedProjectType === "compare" ? 2 : undefined,
              }}
              hoverable
              onClick={() => handleProjectTypeSelection("compare")}
            >
              <RetweetOutlined style={{ fontSize: "2rem" }} />
              <h3>Compare</h3>
            </Card>
          </div>
          {/* Render the 'OK' button only if a project type is selected */}
          {selectedProjectType && (
            <Form.Item>
              <Button type="primary" onClick={handleSubmit}>
                OK
              </Button>
            </Form.Item>
          )}
        </Space>
      </Modal>
      <DragDropCAD visible={showCADModal} onCancel={handleCADModalClose} onCADFiles={console.log} />
    </>
  );
};

export default Questionnaire;






