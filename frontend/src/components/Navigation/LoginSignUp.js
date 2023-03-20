import React from "react";
import { LoginButton } from "../Buttons/LoginButton";
import { SignupButton } from "../Buttons/SignUpButton";
import { Space, Row, Col } from 'antd';

const LoginSignUp = () => {
  return (
    <Row justify="center" align="middle" style={{ height: '100vh' }}>
      <Col xs={24} sm={20} md={16} lg={12} xl={8}>
        <div style={{ backgroundColor: 'white', padding: '20px', boxShadow: '0px 4px 10px rgba(0, 0, 0, 0.1)', borderRadius: '10px' }}>
          <h2>Login or Sign Up</h2>
          <Space wrap>
            <LoginButton />
            <SignupButton />
          </Space>
        </div>
      </Col>
    </Row>
  );
};

export default LoginSignUp;
