let project = new Project("LegendsOfStel");

await project.addProject("./TheEngine");

project.addFile("MyGame/**");
project.addIncludeDir("./MyGame/includes");

project.setDebugDir("Deployment"); // Assets
//project.cmd = true;
project.flatten();

resolve(project);