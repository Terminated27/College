class Song:
    def __init__(self, artist_name: str, song_title: str, song_id: str, duration: float, year: int):      
        '''
        initiate all of the parameters,
        artist_name (str): The name of the artist.
        song_title (str): The title of the song.
        song_id (str): The ID of the song.
        duration (float): The duration of the song in seconds.
        year (int): The year the song was released.

        '''
        self.artist_name = artist_name
        self.song_title = song_title
        self.song_id = song_id
        self.duration = duration
        self.year = year

    def __str__(self):
        '''
        returns a string representation of the class
        '''
        return f"{self.song_title} by {self.artist_name} (ID: {self.song_id}) released in {self.year}"
    def play(self):
        '''
        prints the sing that is playing, and says how long it is
        '''
        print(f"{self.song_title} is playing, with a duration of {self.duration} second(s)")
