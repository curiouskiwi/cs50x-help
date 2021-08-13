## Edit It - CS50x Final Project 2012

Edit It is a web based app that makes it easy to find [flickr](http://flickr.com) photos and edit them in [PicMonkey](http://picmonkey.com).  

[See it in Action](https://www.youtube.com/watch?v=iF9B1fUKmPA)

There are three main sections on the front page: 

### Your Recent Photos

This first feature lets you view your own recent flickr photos, including your private photos, using Flickr's authentication service.  Once you sign in, you can choose how many photos to be retrieved.  [This feature is planned for a future release]

### Search Photos

This  feature lets you search for photos on Flickr, using either tags or text-based searching.  This feature is useful if the photo you want to edit isn't amongst your latest photos, or if you'd like to edit a photo with a Creative Commons or Public Domain license.  I would expect that this would be the goto feature when launching the site, so I've put it right in the middle.

### Upload your own

This feature lets you upload photos directly from your computer to PicMonkey.  I added this feature to make the site more of a "one stop shop" so I could edit photos that I hadn't yet uploaded to flickr.

## Example workflow using Search

Let's say I want to see all of my photos tagged "dog".  I can enter that tag, search, and the results page will show you a small version of the photos.  When you click one, a larger version opens in a pop-up window along with the photo's title, description and tags.

If it's a photo you'd like to edit, you can choose the "Send to PicMonkey" button.  The program will query flickr to find the largest filesize available and open it in PicMonkey.

From there, you can then edit your photo.

### Other features

You can also use Edit It simply as a different interface for searching and viewing flickr photos without any plans for editing.

You can choose to search your own photos, photos from The Commons project or photos with an Attribution-only Creative Commons license.

You can enter tags, choose how many photos to retrieve and sort by either most recent or most interesting.  After getting the matching photos, you can click the thumbails to see larger and click once more to open the photo on the flickr website itself.


## Structure/design of program

Edit It is written mainly in PHP.  Bootstrap is used for layout/style.  Fonts are from Font Awesome.

Main Files:

* _editorv2.php_. This is the main page that is displayed when you load the site.  From there you can choose from the 3 main features described above.  
* _v2get_tagged.php_.  This is called when you choose to search for a photo.  It first calls the flickr api authentication routine and then uses the API to find the photos meeting the criteria you have entered.
* _launch_PM.php_.  This is called by the 'Edit' button.  It will do a flickr API call on the individual photo to determine the largest size available on Flickr so that you can edit that.  It then calls the PicMonkey API which loads the PicMonkey editing interface with the chosen photo.

There are other supporting php files as well.

## Future Development
I want to complete the first feature (editing your own photos).  The flickr authentication API changed while I was building my final project and I didn't have time to rewrite/retest it so I commented it out for now.

## Struggles / Issues
I hadn't really used the flickr API very much and it has a lot of different features/calls, etc.  Took a bit of time to understand the best way to grab the photos I wanted.  To help, I used an open source flickr api php library called DPZ Flickr kit.

_Disclaimer. I work for PicMonkey, but this project is not sponsored nor affiliated with my employer. :)_
