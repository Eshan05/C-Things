// clang-format off

/**
 * Whilst making a website for a hackathon I had this great piece of code which
 takes in the prefix on a URL and then maps into an icon. I used to depict
 social links from JSON data stored in Supabase:
 *
 *  <ul className='space-y-2'>
      {Object.entries(interestsAndLinks.socialmedialinks).map(([platform, url]) => (
        <li key={platform} className='flex items-center space-x-2'>
          {icons[platform] || <GlobeAltIcon className='w-5 h-5' />}
          <a href={url} target="_blank" rel="noopener noreferrer" className='text-sm text-blue-500 hover:underline'> {url}</a>
        </li>
      ))}
      <li className='flex items-center space-x-2'>
        <FaLinkedinIn className='w-5 h-5' />
        <a href={profile.linkedin_link} target="_blank" rel="noopener noreferrer" className='text-sm text-blue-500 hover:underline'> {profile.linkedin_link} </a>
      </li>
    </ul>
 * The icons are taken from
 *  const icons = {
      linkedin: <FaLinkedinIn className='w-5 h-5 ' />,
      twitter: <FaTwitter className='w-5 h-5' />,
      github: <FaGithub className='w-5 h-5 ' />,
      facebook: <FaFacebook className='w-5 h-5 ' />,
    };
 * This is a recreation in C
 */

// clang-format on

#include <locale.h>
#include <stdio.h>

int s_strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2) return (*s1 - *s2);
    s1++;
    s2++;
  }
  return (*s1 - *s2);
}

char *s_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') return (char *)haystack;
  while (*haystack) {
    const char *h = haystack;
    const char *n = needle;
    while (*n && (*h == *n)) {
      h++;
      n++;
    }
    if (*n == '\0') return (char *)haystack;
    haystack++;
  }
  return NULL;
}

typedef struct {
  const char *platform;
  const char *url;
  const char *icon;
} SocialMediaLink;

const char *detectPlatform(const char *url) {
  if (s_strstr(url, "facebook.com")) return "Facebook | [F]";
  else if (s_strstr(url, "twitter.com")) return "Twitter | [X]";
  else if (s_strstr(url, "instagram.com")) return "Instagram | [I]";
  else if (s_strstr(url, "github.com")) return "Github | ";
  else if (s_strstr(url, "linkedin.com")) return "Linkedin | [L]";
  else return "Unknown | [?]";
}

void printLinks(const char *urls[], int size) {
  for (int i = 0; i < size; i++) {
    const char *result = detectPlatform(urls[i]);
    char platform[15], icon[31];
    sscanf(result, "%14[^|]|%30s", platform, icon);
    printf("%s %s: %s\n", icon, platform, urls[i]);
  }
}

int main() {
  setlocale(LC_CTYPE, "");
  const char *urls[] = { "https://facebook.com/d", "https://twitter.com/d",
                         "https://instagram.com/d", "https://linkedin.com/in/d",
                         "https://yourwebsite.com" };
  int n = sizeof(urls) / sizeof(urls[0]);
  printf("Social Links:\n");
  printLinks(urls, n);
  return 0;
}