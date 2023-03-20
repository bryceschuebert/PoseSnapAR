import React from "react";
import { Modal, Form, Input, Button } from "antd";

const ProjectModal = ({ visible, onSelectProject, onCancel }) => {
  const [form] = Form.useForm();

  const handleCreateProject = () => {
    const projectData = form.getFieldValue("projectName");
    onSelectProject(projectData);
  };

  return (
    <Modal
      title="Create or Open Project"
      visible={visible}
      onCancel={onCancel}
      footer={null}
    >
      <Form form={form} layout="vertical" onFinish={handleCreateProject}>
        <Form.Item
          label="Project Name"
          name="projectName"
          rules={[{ required: true, message: "Please input a project name!" }]}
        >
          <Input />
        </Form.Item>
        <Form.Item>
          <Button type="primary" htmlType="submit">
            Create Project
          </Button>
        </Form.Item>
      </Form>
    </Modal>
  );
};

export default ProjectModal;
