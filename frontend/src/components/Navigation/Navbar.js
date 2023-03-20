import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import { useAuth0 } from '@auth0/auth0-react';
import LogoutButton from '../Buttons/LogOutButton';
import { Layout, Menu, Button, Dropdown } from 'antd';

const { Header } = Layout;

const NavBar = ({ onNewProject }) => {
  const { isAuthenticated, user } = useAuth0();
  const [isDropdownVisible, setDropdownVisible] = useState(false);

  const handleMouseEnter = () => {
    setDropdownVisible(true);
  };

  const handleMouseLeave = () => {
    setDropdownVisible(false);
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
      <div style={{ display: 'flex', justifyContent: 'space-between' }}>
        <div style={{ display: 'flex' }}>
          <Button type="text" onClick={onNewProject}>
            New
          </Button>
          <Button type="text" onClick={onNewProject}>
            Open
          </Button>
        </div>
        {isAuthenticated ? (
          <Dropdown
            overlay={menu}
            onVisibleChange={setDropdownVisible}
            visible={isDropdownVisible}
          >
            <Button>
              Hi, {user.name}
            </Button>
          </Dropdown>
        ) : (
          <Button>
            <Link to="/login-signup">Login</Link>
          </Button>
        )}
      </div>
    </Header>
  );
};

export default NavBar;



