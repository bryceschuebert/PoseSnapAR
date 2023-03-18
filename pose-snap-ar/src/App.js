import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import Homepage from './components/Homepage/Homepage';
import ProtectedRoute from './components/ProtectedRoute/ProtectedRoute';
import Login from './components/Login/Login';
import Registration from './components/Registration/Registration';

const App = () => {
  const isAuthenticated = false; // Replace this with the actual authentication status

  return (
    <Router>
      <Routes>
        <ProtectedRoute exact path="/" component={Homepage} isAuthenticated={isAuthenticated} />
        <Route path="/login" component={Login} />
        <Route path="/" element={<Homepage />} />
        <Route path="/registration" element={<Registration />} />
      </Routes>
    </Router>
  );
}

export default App;

