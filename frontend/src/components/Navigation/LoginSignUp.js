// src/components/LoginSignUp/LoginSignUp.js

import React from "react";
import { LoginButton } from "../Buttons/LoginButton";
import { SignupButton } from "../Buttons/SignUpButton";

const LoginSignUp = () => {
  return (
    <div className="login-sign-up">
      <h2>Login or Sign Up</h2>
      <LoginButton />
      <SignupButton />
    </div>
  );
};

export default LoginSignUp;
