import React, { useState } from "react";
import "../../styles/navbarStyles.css";
import { NavBarButtons } from "./NavBarButtons";

const Navbar = () => {
  const [activeDropdown, setActiveDropdown] = useState("");

  return (
    <nav className="navbar">
      <div className="left-side">
        {/* Other left-side elements */}
      </div>
      <NavBarButtons />
      <div className={`backdrop ${activeDropdown !== '' ? 'visible' : ''}`} onClick={() => setActiveDropdown('')}></div>
    </nav>
  );
};

export default Navbar;



