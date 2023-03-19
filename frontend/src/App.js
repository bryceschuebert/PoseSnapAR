import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import ProtectedRoute from './components/ProtectedRoute/ProtectedRoute';
import Homepage from './components/Homepage/Homepage';
import Login from './components/Login/Login';

const App = () => {
  return (
    <Router>
      <Routes>
       <ProtectedRoute path="/" element={<Homepage />} />
        <Route path="/login" element={<Login />} />
      </Routes>
    </Router>
  );
};

export default App;



