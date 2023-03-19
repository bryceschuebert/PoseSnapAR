import React from "react";
import Navbar from "./Navigation/Navbar.js";

export const CallbackPage = () => {
  return (
    <div className="page-layout">
      <Navbar />
      <div className="page-layout__content" />
    </div>
  );
};

export default CallbackPage;