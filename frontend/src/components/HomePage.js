import React from 'react';
import { useAuth0 } from '@auth0/auth0-react';

const HomePage = () => {
  const { user, isAuthenticated, loginWithRedirect, logout } = useAuth0();

  return (
    <div className="HomePage">
      {isAuthenticated ? (
        <>
          <div>
            <img src={user.picture} alt={user.name} />
            <h2>{user.name}</h2>
            <p>{user.email}</p>
          </div>
          <button onClick={() => logout({ returnTo: window.location.origin })}>
            Log Out
          </button>
        </>
      ) : (
        <button onClick={loginWithRedirect}>Log In</button>
      )}
    </div>
  );
};

export default HomePage;
