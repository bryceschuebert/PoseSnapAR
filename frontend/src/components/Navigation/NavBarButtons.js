import React from "react";
import { useAuth0 } from "@auth0/auth0-react";
import { LoginButton } from "../Buttons/LoginButton";
import { LogoutButton } from "../Buttons/LogOutButton";
import { SignupButton } from "../Buttons/SignUpButton";

export const NavBarButtons = () => {
  const { isAuthenticated } = useAuth0();

  return (
    <div className="nav-bar-buttons">
      {!isAuthenticated && (
        <>
          <LoginButton />
          <SignupButton />
        </>
      )}
      {isAuthenticated && <LogoutButton />}
    </div>
  );
};

export default NavBarButtons;
