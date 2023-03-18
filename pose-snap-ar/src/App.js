// App.js
import React from 'react';
import { BrowserRouter as Router, Route, Routes, Navigate } from 'react-router-dom';
import Homepage from './components/Homepage/Homepage';
import Login from './components/Login/Login';
import Registration from './components/Registration/Registration';

const App = () => {
  const isAuthenticated = false; // Replace this with the actual authentication status

  const ProtectedHomepage = () => {
    return isAuthenticated ? <Homepage /> : <Navigate to="/login" replace />;
  };

  return (
    <Router>
      <Routes>
        <Route path="/" element={<ProtectedHomepage />} />
        <Route path="/login" element={<Login />} />
        <Route path="/registration" element={<Registration />} />
      </Routes>
    </Router>
  );
};

export default App;



