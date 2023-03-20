import React from 'react';
import { Route, Routes, useLocation } from 'react-router-dom';
import { useAuth0 } from '@auth0/auth0-react';
import Loading from './components/Loading';
import Account from './components/Account';
import ProjectPage from './components/Project/ProjectPage';
import Navbar from './components/Navigation/Navbar';
import HomePage from './components/HomePage';
import LoginSignUp from './components/Navigation/LoginSignUp';
import MobileWarning from './components/MobileWarning';

function App() {
  const { isLoading } = useAuth0();
  const location = useLocation();

  if (isLoading) {
    return <Loading />;
  }

  return (
    <div className="App">
      <MobileWarning />
      {location.pathname !== '/login-signup' && <Navbar />}
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/account" element={<Account />} />
        <Route path="/projects" element={<ProjectPage />} />
        <Route path="/login-signup" element={<LoginSignUp />} />
      </Routes>
    </div>
  );
}

export default App;
 






