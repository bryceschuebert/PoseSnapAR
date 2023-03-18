// ProtectedRoute.js
import React from 'react';
import { Navigate, Route } from 'react-router-dom';

const ProtectedRoute = ({ isAuthenticated, ...props }) => {
  return isAuthenticated ? <Route {...props} /> : <Navigate to="/login" replace />;
};

export default ProtectedRoute;





