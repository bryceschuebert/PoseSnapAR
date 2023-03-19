// Navbar.js

import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import '../styles/navbarStyles.css';

const Navbar = () => {
  const [activeDropdown, setActiveDropdown] = useState('');

  return (
    <nav className="navbar">
      <ul>
        <li onMouseEnter={() => setActiveDropdown('home')} onMouseLeave={() => setActiveDropdown('')}>
          <Link to="/">Home</Link>
        </li>
        <li onMouseEnter={() => setActiveDropdown('account')} onMouseLeave={() => setActiveDropdown('')}>
          <Link to="/account">Account</Link>
        </li>
        <li onMouseEnter={() => setActiveDropdown('projects')} onMouseLeave={() => setActiveDropdown('')}>
          <Link to="/projects">Projects</Link>
        </li>
        <div className={`backdrop ${activeDropdown !== '' ? 'visible' : ''}`} onClick={() => setActiveDropdown('')}></div>
      </ul>
    </nav>
  );
};

export default Navbar;


