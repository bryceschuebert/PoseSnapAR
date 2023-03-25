import { useLocation } from 'react-router-dom';

const CompareProject = () => {
  const location = useLocation();
  const cadFiles = location.state?.cadFiles;

  return (
    <div>
      <h1>Compare Project</h1>
      {/* Process the CAD files and render the project content */}
      {cadFiles.map((file) => (
        <p key={file.name}>{file.name}</p>
      ))}
    </div>
  );
};

export default CompareProject;