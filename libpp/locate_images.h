/**
 * @file locate_images.h
 * Location of binary images
 *
 * @remark Copyright 2002 OProfile authors
 * @remark Read the file COPYING
 *
 * @author Philippe Elie
 * @author John Levon
 */

#ifndef LOCATE_IMAGES_H
#define LOCATE_IMAGES_H

#include <string>
#include <map>
#include <vector>

/**
 * A class containing mappings from an image basename,
 * such as 'floppy.ko', to locations in the paths passed
 * in to populate().
 *
 * The name may exist multiple times; all locations are recorded
 * in this container.
 */
class extra_images {
public:
	extra_images() {}

	/// add all filenames found in the given paths, recursively
	void populate(std::vector<std::string> const & paths);	

	/// base class for matcher functors object
	struct matcher {
		std::string const & value;
	public:
		explicit matcher(std::string const & v) : value(v) {}
		/// default functor allowing trivial match
		virtual bool operator()(std::string const & str) const {
			return str == value;
		}
	};

	/**
	 * return a vector of all directories that match the functor
	 */
	std::vector<std::string> const find(matcher const & match) const;

	/// return a vector of all directories that match the given name
	std::vector<std::string> const find(std::string const & name) const;

private:
	typedef std::multimap<std::string, std::string> images_t;
	typedef images_t::value_type value_type;
	typedef images_t::const_iterator const_iterator;

	/// map from image basename to owning directory
	images_t images;
};


/**
 * @param extra_images container where all extra candidate filenames are stored
 * @param image_name binary image name
 * @param ok return failure/success, in case of failure the returned string
 *  is identical to image_name
 *
 * Locate a (number of) matching absolute paths to the given image name.
 * If we fail to find the file or if it is not readable we provide a warning
 * and return an empty string.
 */
std::string const find_image_path(std::string const & image_name,
                            extra_images const & extra_images, bool & ok);
#endif /* LOCATE_IMAGES_H */
