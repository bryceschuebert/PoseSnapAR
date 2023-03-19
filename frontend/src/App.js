// App.js
import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import { useAuth0 } from '@auth0/auth0-react';
import Loading from './components/Loading';
import HomePage from './components/HomePage';
import Account from './components/Account';
import ProjectPage from './components/Project/ProjectPage'; // Import ProjectPage component
import Navbar from './components/Navbar';

function App() {
  const { isLoading } = useAuth0();

  if (isLoading) {
    return <Loading />;
  }

  return (
    <div className="App">
      <Router>
        <Navbar />
        <Routes>
          <Route path="/" element={<HomePage />} />
          <Route path="/account" element={<Account />} />
          <Route path="/projects" element={<ProjectPage />} />
        </Routes>
      </Router>
    </div>
  );
}

export default App;






