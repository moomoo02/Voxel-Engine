#!/usr/bin/env node

const fs = require('fs');
const path = require('path');

const ROOT_DIR = './Memories';
const README_FILENAME = 'README.md';
const NB_IMAGES_PER_LINE = 4;
let nbImages = 0;

let introduction = '# My Learning OpenGL Journey \nHello, this is where I\'m learning OpenGl.  Since I will be always changing the code around to learn new concepts, I want to keep in memory all the graphics that I produced.  Below is my journey of every graphic I created, sorted from earliest to latest. \n '
let mdContent = introduction + '<table><tr>';
let journal = fs.readFileSync('./journal.md', 'utf8');

const getSortedFiles = async (dir) => {
    const files = await fs.promises.readdir(dir);
    
    return files
      .map(fileName => ({
        name: fileName,
        time: fs.statSync(`${dir}/${fileName}`).mtime.getTime(),
      }))
      .sort((a, b) => a.time - b.time);

};

const parseDate = (timeInMilliseconds) => {
    var date = new Date(timeInMilliseconds);
    return date.toString().substring(4,15);
}
getSortedFiles(ROOT_DIR).then((result) => {
    //console.log(result);
    console.log(result);
    result.forEach((image) => {
        if (image.name !== README_FILENAME) {
            if (!(nbImages % NB_IMAGES_PER_LINE)) {
                if (nbImages > 0) {
                    mdContent += `</tr>`;
                }
                mdContent += `<tr>`;
            }
            
            nbImages++;
            mdContent += `
            <td valign="bottom">
            <img src="./Memories/${image.name}" width="200"><br>
            ${image.name} | ${parseDate(image.time)}
            </td>`;
        }
     });
     mdContent += `</tr></table>\n`;
     mdContent += journal;
     fs.writeFileSync(path.join("./", README_FILENAME), mdContent);
});
