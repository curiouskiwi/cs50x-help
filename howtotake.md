%%{ init: { 'graph': { 'curve': 'stepAfter' } } }%%
flowchart TD
    classDef default fill:ivory, stroke:none
    classDef optional color:firebrick,stroke:crimson,stroke-width:.1px;
    classDef required color:white, stroke:blue,stroke-width:1px,fill:firebrick;
    classDef title color:firebrick, stroke-width:2px,font-size:large, font-weight:bold;
    classDef footnote color:gray
    Complete ~~~ Lecture
    Lecture-->SectionO
    SectionO-->Shorts
    Shorts -->Pset
    Pset ~~~ Practice0
    Practice0 ~~~ Footnote


subgraph  
Complete[fa:fa-check How to complete a week<BR>in CS50x 2024]:::title
Lecture[fa:fa-video Watch Lecture]:::required 
SectionO[fa:fa-video Watch Section]:::required
Shorts[fa:fa-video Watch any/all Shorts <br> for more in depth study fa:fa-question-circle]:::optional
Pset[fa:fa-file-code Submit Problem Set]:::required
Practice0["fa:fa-user-check Want more practice? <br> Optionally, complete Practice problems <br> before or after the Problem Set"]:::optional
Footnote["Note. Sections begin Week 1"]:::footnote
end
