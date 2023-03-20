import { useAuth0 } from "@auth0/auth0-react";
import React from "react";

export const Account = () => {
  const { user } = useAuth0();

  if (!user) {
    return null;
  }

  return (
    <div>
      <h1>Profile Page</h1>
      <p>
        You can use the <strong>ID Token</strong> to get the profile
        information of an authenticated user.
      </p>
      <p>
        <strong>Only authenticated users can access this page.</strong>
      </p>
      <div>
        <img src={user.picture} alt="Profile" />
        <h2>{user.name}</h2>
        <span>{user.email}</span>
      </div>
      <div>
        <pre>{JSON.stringify(user, null, 2)}</pre>
      </div>
    </div>
  );
};

export default Account;
