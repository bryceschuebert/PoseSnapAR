import { Tree } from 'antd';
import { LoadingOutlined } from '@ant-design/icons';

const ConversionProgress = () => {
    const treeData = [
      {
        title: 'Converting CAD file',
        key: '0',
        icon: <LoadingOutlined />,
        children: [
          {
            title: 'Loading...',
            key: '0-0',
          },
        ],
      },
    ];
  
    return (
      <Tree
        showIcon
        defaultExpandedKeys={['0']}
        treeData={treeData}
      />
    );
  };
  
  export default ConversionProgress;
  