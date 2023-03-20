import React from 'react';
import { Link, useLocation, useNavigate } from 'react-router-dom';
import { useAuth0 } from '@auth0/auth0-react';
import LogoutButton from '../Buttons/LogOutButton';
import NewProjectButton from '../Buttons/NewProjectButton';
import OpenProjectButton from '../Buttons/OpenProjectButton';
import { Row, Col, Layout, Menu, Dropdown, Button, Space } from 'antd';
import { DownOutlined } from '@ant-design/icons';
import styles from '../Buttons/button.module.css';

const { Header } = Layout;

const NavBar = ({ onNewProject, onOpenProject }) => {
  const { isAuthenticated, user } = useAuth0();
  const location = useLocation();
  const navigate = useNavigate();
  const onAccountPage = location.pathname === '/account';

  const handleBack = () => {
    navigate(-1);
  };

  const menu = (
    <Menu>
      <Menu.Item>
        <Link to="/account">Account</Link>
      </Menu.Item>
      <Menu.Item>
        <LogoutButton />
      </Menu.Item>
    </Menu>
  );

  return (
    <Header>
      <Row justify="center">
        <Col xs={24} sm={20} md={16} lg={12} xl={8}>
          <div
            style={{
              display: 'flex',
              justifyContent: 'space-between',
              alignItems: 'center',
              height: '100%',
            }}
          >
            <div style={{ display: 'flex' }}>
              {onAccountPage ? (
                <Button onClick={handleBack}>Back</Button>
              ) : (
                <>
                  <NewProjectButton onClick={onNewProject} />
                  <OpenProjectButton onClick={onOpenProject} />
                </>
              )}
            </div>
            {isAuthenticated ? (
              <Dropdown overlay={menu} className={styles.navText}>
                <a onClick={(e) => e.preventDefault()}>
                  <Space>
                    Hi, {user.name}
                    <DownOutlined />
                  </Space>
                </a>
              </Dropdown>
            ) : (
              <Button>
                <Link to="/login-signup">Login</Link>
              </Button>
            )}
          </div>
        </Col>
      </Row>
    </Header>
  );
};

export default NavBar;



