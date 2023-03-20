import React from "react";
import { Form, Input, Button, Modal, Radio } from "antd";

const Questionnaire = ({ onSubmit, visible, onCancel }) => {
  const [form] = Form.useForm();

  const handleFinish = (values) => {
    onSubmit(values);
  };

  return (
    <Modal
      title="New Project"
      visible={visible}
      onCancel={onCancel}
      footer={null}
      centered
    >
      <Form form={form} layout="vertical" onFinish={handleFinish}>
        <Form.Item
          label="Select Project Type"
          name="projectType"
          rules={[{ required: true, message: "Please select a project type!" }]}
        >
          <Radio.Group>
            <Radio.Button value="pose">Pose</Radio.Button>
            <Radio.Button value="compare">Compare</Radio.Button>
          </Radio.Group>
        </Form.Item>
        {/* Add more questions as needed */}
        <Form.Item
          label="Question 1"
          name="question1"
          rules={[{ required: true, message: "Please provide an answer!" }]}
        >
          <Input />
        </Form.Item>
        <Form.Item>
          <Button type="primary" htmlType="submit">
            Submit
          </Button>
        </Form.Item>
      </Form>
    </Modal>
  );
};

export default Questionnaire;
