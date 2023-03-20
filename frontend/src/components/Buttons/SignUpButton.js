import { useAuth0 } from "@auth0/auth0-react";
import React from "react";
import { Button } from "antd";

export const SignupButton = () => {
  const { loginWithRedirect } = useAuth0();

  const handleSignUp = async () => {
    await loginWithRedirect({
      appState: {
        returnTo: "/projects",
      },
      authorizationParams: {
        screen_hint: "signup",
      },
    });
  };

  return (
    <Button type="default" size="large" onClick={handleSignUp}>
      Sign Up
    </Button>
  );
};

export default SignupButton;
