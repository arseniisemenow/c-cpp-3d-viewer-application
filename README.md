## 3DViewer v1.0 Project Overview

### Introduction
This application, 3DViewer v1.0, is crafted to streamline the visualization of 3D wireframe models. Developed in C language with a dedicated focus on the Qt framework, it follows structured programming and adheres to Google style guidelines, offering a rich set of features for efficient 3D model interaction.

### Features and Capabilities
- **Model Loading**: The application empowers users to load 3D wireframe models from .obj files, emphasizing support for vertices and surfaces lists as a foundational structure.

![model-loading_YSeTc7WC.gif](model-loading_YSeTc7WC.gif)

- **Manipulation Tools**: Users can seamlessly interact with loaded models through essential manipulation tools:
    - **Translation**: Move the model along the X, Y, Z axes by a specified distance.
    - **Rotation**: Rotate the model around its X, Y, Z axes by a given angle.
    - **Scaling**: Adjust the model's size proportionally.
![manipulation-tools_UKKE5bJM.gif](manipulation-tools_UKKE5bJM.gif)
- **Qt-Based GUI**: The graphical user interface is implemented using the Qt framework, providing an aesthetically pleasing and intuitive environment. Key interface elements include:
    - **File Selection**: A button to select the model file, accompanied by a field displaying its name.
    - **Visualization Area**: A dedicated space for viewing the wireframe model.
    - **Manipulation Controls**: Buttons and input fields for translation, rotation, and scaling.
    - **Model Information**: Display of file name, number of vertices, and edges.

### Performance and Compatibility
- **Optimized Handling**: The program is optimized to handle models with varying complexities, from 100 to 1,000,000 vertices, ensuring smooth performance without interface freezing.

### Bonus Features - Settings
#### Customization Options:
- **Projection Type**: Choose between parallel and central projection for a tailored viewing experience.
- **Edge Configuration**: Customize edge type (solid, dashed), color, and thickness.
- **Vertex Display**: Configure the display of vertices with options for type (none, circle, square), color, and size.
- **Background Color**: Personalize the background color to suit preferences.
- **Persistent Settings**: Enjoy the convenience of settings that persist between program restarts.
![customization-options_Lh4blB6u.gif](customization-options_Lh4blB6u.gif)
### Bonus Features - Record
#### Image Capture and Animation:
- **Image Saving**: Capture and save rendered images as BMP and JPEG files.
- **Screencast Recording**: Record small screencasts with a special button, creating GIF animations (640x480, 10fps, 5s) showcasing custom affine transformations of loaded objects.

In summary, 3DViewer v1.0, built on the Qt framework, provides a robust platform for working with 3D wireframe models. It offers essential manipulation tools, a user-friendly Qt-based interface, and additional customization options for an enriched user experience.