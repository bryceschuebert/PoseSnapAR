import { useAuth0 } from "@auth0/auth0-react";
import React from "react";
import { Button } from "antd";

export const LoginButton = () => {
  const { loginWithRedirect } = useAuth0();

  const handleLogin = async () => {
    await loginWithRedirect({
      appState: {
        returnTo: "/projects",
      },
    });
  };

  return (
    <Button type="primary" onClick={handleLogin}>
      Log In
    </Button>
  );
};

export default LoginButton;
