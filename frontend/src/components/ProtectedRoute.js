// src/components/ProtectedRoute.js

import React from "react";
import { Route, Navigate } from "react-router-dom";
import { useAuth0 } from "@auth0/auth0-react";

const ProtectedRoute = ({ element, ...rest }) => {
  const { isAuthenticated } = useAuth0();

  return (
    <Route
      {...rest}
      render={() =>
        isAuthenticated ? element : <Navigate to="/login-signup" replace />}
    />
  );
};

export default ProtectedRoute;
