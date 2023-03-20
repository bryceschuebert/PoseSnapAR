import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import { useAuth0 } from '@auth0/auth0-react';
import LogoutButton from '../Buttons/LogOutButton';
import { Layout, Menu } from "antd";

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

  return (
    <Header>
      <Menu mode="horizontal" theme="dark">
        {isAuthenticated && (
          <>
            <Menu.Item key="new" onClick={onNewProject}>
              New
            </Menu.Item>
            <Menu.Item key="open" onClick={onNewProject}>
              Open
            </Menu.Item>
          </>
        )}
        {isAuthenticated && (
          <div
            onMouseEnter={handleMouseEnter}
            onMouseLeave={handleMouseLeave}
            className="user-dropdown"
          >
            <span>Hi, {user.name}</span>
            {isDropdownVisible && (
              <div className="user-dropdown-menu">
                <Link to="/account">Account</Link>
                <LogoutButton />
              </div>
            )}
          </div>
        )}
      </Menu>
    </Header>
  );
};

export default NavBar;



