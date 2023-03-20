import React from 'react';
import { Link, useLocation, useNavigate } from 'react-router-dom';
import { useAuth0 } from '@auth0/auth0-react';
import LogoutButton from '../Buttons/LogOutButton';
import NewProjectButton from '../Buttons/NewProjectButton';
import OpenProjectButton from '../Buttons/OpenProjectButton';
import { Row, Col, Layout, Menu, Dropdown, Button, Space } from 'antd';
import { DownOutlined } from '@ant-design/icons';
import styles from '../Buttons/button.module.css';
import navbarStyles from './navbar.module.css';

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
    <Header className={navbarStyles.customHeader} style={{ display: 'flex', alignItems: 'center' }}>
      <Row style={{ width: '100%' }}>
        <Col span={6}>
          <div style={{ display: 'flex', justifyContent: 'flex-start' }}>
            {onAccountPage ? (
              <Button type="link" className={styles.navText} onClick={handleBack}>Back</Button>
            ) : (
              <>
                <NewProjectButton onClick={onNewProject} />
                <OpenProjectButton onClick={onOpenProject} />
              </>
            )}
          </div>
        </Col>
        <Col span={8} offset={8}>
          <div style={{ display: 'flex', justifyContent: 'flex-end' }}>
            {isAuthenticated ? (
              <Dropdown overlay={menu} className={styles.navText}>
                <Button
                  onClick={(e) => e.preventDefault()}
                  type="link"
                  className={styles.navText}
                >
                  <Space>
                    Hi, {user.name}
                    <DownOutlined />
                  </Space>
                </Button>
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





