import { useAuth0 } from "@auth0/auth0-react";
import React from "react";
import { LoginButton } from "../Buttons/LoginButton";
import { LogoutButton } from "../Buttons/LogOutButton";
import { SignupButton } from "../Buttons/SignUpButton";

export const MobileNavBarButtons = () => {
  const { isAuthenticated } = useAuth0();

  return (
    <div className="mobile-nav-bar__buttons">
      {!isAuthenticated && (
        <>
          <SignupButton />
          <LoginButton />
        </>
      )}
      {isAuthenticated && (
        <>
          <LogoutButton />
        </>
      )}
    </div>
  );
};

export default MobileNavBarButtons;