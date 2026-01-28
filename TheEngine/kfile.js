const path = require('path');
const fs = require('fs');
const { hasSubscribers } = require('diagnostics_channel');
const { error } = require('console');


// Fist of all, re sync Assets 
//Clean all Assets in Deployment
emptyDirectory("./Deployment/Assets")

//Verify if MyGame/Assets exist and create otherelse 
checkMyGameAssets()

//Re-sync all Assets to project
try{
    fs.cpSync("./MyGame/Assets", "./Deployment/Assets", {recursive : true, force: true});
    console.log('All files and subdirectories copied successfully!');
}catch(err){
    console.error('Error copying Assets files:', err);
}

function emptyDirectory(dirPath) {
    hasDirectory = fs.existsSync(dirPath);

    if(hasDirectory) {
        console.log('Directory Assets exists!');

        try {
            const files = fs.readdirSync(dirPath);

            for (const file of files) {
                const filePath = path.join(dirPath, file);
                // Use fs.rmSync() with recursive: true to handle files and directories
                fs.rmSync(filePath, { recursive: true, force: true }); 
            }
            console.log(`All files in ${dirPath} deleted synchronously.`);
        } catch (error) {
            console.error(`Error deleting files synchronously: ${error.message}`);
        }
    }else {
        console.log('Directory Assets not found.');
        fs.mkdirSync(dirPath, { recursive: true });
        console.log('Directory Assets created successfully!');
    }
}

function checkMyGameAssets() {
    if(!fs.existsSync("./MyGame/Assets")){
        fs.mkdirSync("./MyGame/Assets", { recursive: true });
        console.log('Directory Game Assets created successfully!');
    }
}


// Then create project
let project = new Project('engine');
 
project.addProvider = function(proj, isRoot=false){
    const sdl2 = true;//process.argv.indexOf("--sdl2") >= 0;
    if(sdl2){
        
        if(!isRoot){
            proj.addDefine("USE_SDL");
            // proj.addDefine("_DEBUG");
            //proj.addDefine("_RELEASE");
            proj.addIncludeDir(path.resolve("./SDL/include"));
        }
        proj.addLib("../SDL/lib/SDL2");
        proj.addLib("../SDL/lib/SDL2main");
        proj.addLib("../SDL/lib/SDL2_image");
        proj.addLib("../SDL/lib/SDL2_ttf");
        proj.addLib("../SDL/lib/SDL2_mixer");
        if(!fs.existsSync("./Deployment/SDL2.dll")) {
            fs.copyFileSync("./SDL/lib/SDL2.dll", "./Deployment/SDL2.dll") 
            fs.copyFileSync("./SDL/lib/SDL2_image.dll", "./Deployment/SDL2_image.dll")
            fs.copyFileSync("./SDL/lib/SDL2_ttf.dll", "./Deployment/SDL2_ttf.dll")
            fs.copyFileSync("./SDL/lib/SDL2_mixer.dll", "./Deployment/SDL2_mixer.dll")
        }
    }

};
project.kore = false;


project.addDefine("KINC_STATIC_COMPILE");
project.isStaticLib = true;

project.addIncludeDir(path.resolve("./TheEngine/includes"));
project.addFiles('sources/**','includes/**');

project.addIncludeDir("C:/Program Files (x86)/Visual Leak Detector/include");
project.addLib("C:/Program Files (x86)/Visual Leak Detector/lib/Win64/vld");
project.addProvider(project,false);

resolve(project);
