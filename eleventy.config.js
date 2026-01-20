export default async function (eleventyConfig) {
    eleventyConfig.setInputDirectory("eleventy");
    eleventyConfig.addPassthroughCopy("eleventy/attachments");
};