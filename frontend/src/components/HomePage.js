// components/HomePage.js
import { useEffect } from "react";
import { useAuth0 } from "@auth0/auth0-react";
import { useNavigate } from "react-router-dom";

const HomePage = () => {
  const { isAuthenticated } = useAuth0();
  const navigate = useNavigate();

  useEffect(() => {
    if (isAuthenticated) {
      navigate("/projects");
    } else {
      navigate("/login-signup");
    }
  }, [isAuthenticated, navigate]);

  return null;
};

export default HomePage;

